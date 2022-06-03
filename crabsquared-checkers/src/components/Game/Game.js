import React from 'react';
import { cloneDeep } from 'lodash';
import './Game.css';

import Board from '../Board/Board';
import InfoPanel from '../InfoPanel/InfoPanel';
import Move from './Move';

export default class Game extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            board: [
                ['b','.','b','.','b','.','b','.'],
                ['.','b','.','b','.','b','.','b'],
                ['b','.','b','.','b','.','b','.'],
                ['.','.','.','.','.','.','.','.'],
                ['.','.','.','.','.','.','.','.'],
                ['.','w','.','w','.','w','.','w'],
                ['w','.','w','.','w','.','w','.'],
                ['.','w','.','w','.','w','.','w']
            ],
            
            activePlayer: 'w',

            chosenBot: 'bot_random',

            /** Position of a piece to be moved. */
            chosenPiece: null,

            /** Chosen piece color */
            chosenPieceColor: null,

            /** List of paths that describes possible moves for a chosen piece. */
            availablePaths: null,

            /** Path of squares travelled by currently chosenPiece */
            pathTravelled: [],

            availableStarts: [],
        }
        this.handleSquareClick = this.handleSquareClick.bind(this);
        this.handleUndoClick = this.handleUndoClick.bind(this);

        /** Contains all game states previous to the current one. */
        this.history = [];

        /** Helps handle moves. */
        this.move = new Move(this);
        
        this.move.fetchAvailableMoves().then(
            availableStarts => {
                this.setState({
                ...this.state,
                availableStarts: availableStarts
            });
        }
        );

        this.click_sound = new Audio('/click.wav');

        this.error_sound = new Audio('/error.wav');

        this.bot_sound = new Audio('/bot_move.wav');
    }

    getBoard() {
        return this.state.board;
    }

    getActivePlayer() {
        this.setState({
            ...this.state,
            availableStarts: [],
        });
        return this.state.activePlayer;
    }

    getChosenPiece() {
        return this.state.chosenPiece;
    }

    getChosenPieceColor() {
        return this.state.chosenPieceColor;
    }

    getAvailablePaths() {
        return this.state.availablePaths;
    }

    getPathTravelled() {
        return this.state.pathTravelled;
    }

    /**
     * Returns the opponent of the active player. 
     */
    getOpponent() {
        return this.state.activePlayer === 'w' ? 'b' : 'w';
    }

    /**
     * Returns flattened list of available paths, i.e. list of arrays of form [x, y].
     */
    getAvailableSquares() {
        return this.state.availablePaths ? this.state.availablePaths.flat() : [];
    }

    /**
     * Returns whether a move is in progress.
     * Move is in progress when path travelled is not empty.
     */
    #isMoveInProgress() {
        return this.state.pathTravelled.length > 0;
    }

    // If current player has no move - print winner
    #handleEndGame() {
        // flat board to check for white pieces
        if (this.state.board.flat().filter(piece => piece === 'w' || piece === 'W').length === 0) {
            alert("Black wins!");
            return;
        }
        // flat board to check for black pieces
        if (this.state.board.flat().filter(piece => piece === 'b' || piece === 'B').length === 0) {
            alert("White wins!");
            return;
        }
        return;
    }

    /**
     * Handles a choose of a piece.
     * @param {*} position - clicked position
     * @returns whether a piece was choosen successfully
     */
    #choosePiece(position) {
        if (this.state.board.atPosition(position).toLowerCase() === this.state.activePlayer) {
            this.setState(this.move.choosePiece(position));
            return true;
        }
        return false;
    }

    /**
     * Returns whether a piece was already chosen.
     */
    #isPieceChosen() {
        return this.state.chosenPiece !== null;
    }

    /**
     * Checks whether a position is available to the chosen piece in a single jump.
     * It looks for a path that starts with a clicked position amongst available paths.
     * @param {*} position - clicked position
     */
    #isAvailable(position) {
        return this.getAvailablePaths().some(([first, ..._]) => position.isEqual(first));
    }

    /**
     * Moves chosen piece to a clicked position if the position is available.
     * @param {*} position - clicked position
     */
    #movePiece(position) {
        if (this.#isAvailable(position)) {
            this.history.push(cloneDeep(this.state));
            this.setState(this.move.jumpOn(position));
        }
    }

    /**
     * Fetches a bot move from the server and executes it.
     * After the last jump, it fetches available moves for the player.
     */
    executeBotMove() {
        return this.move.chooseBotPiece().then(state => {
            // bot chooses a piece
            this.setState(state);
            
            this.#handleEndGame();
            
            // bot has only one available path
            const botPath = this.state.availablePaths[0];
            botPath.forEach((pos, index) => {
                setTimeout(p => {
                    this.bot_sound.play();
                    this.setState(
                        this.move.jumpOn(p),
                        // if it is the last jump and the setState finishes, 
                        // fetch available moves
                        () => {
                            if (index === botPath.length - 1) 
                                this.move.fetchAvailableMoves().then(
                                    availableStarts => {
                                        this.setState({
                                        ...this.state,
                                        availableStarts: availableStarts
                                    });
                                }
                                );
                        }
                    );
                }, 500, pos);
            });
        }, () => {
            this.#handleEndGame();
        });
    }

    /**
     * Check if it's a bot's turn and perform a bot move if it is.
     */
    componentDidUpdate() {
        if (this.state.activePlayer === 'b' && !this.#isPieceChosen()) {
            this.executeBotMove().then(() => {
                this.#handleEndGame();
            });
        }        
    }

    /**
     * Handles a square click.
     * If there is a move in progress tries to move chosen piece to the clicked position.
     * Otherwise, it tries to choose a piece (possibly replacing the current one)
     * and if the choose of a new piece was not successfull, if there already is a chosen piece,
     * it tries to move it to the clicked position (start the move).
     * @param {*} position - clicked position
     */
    handleSquareClick(position) {
        if (this.state.activePlayer === 'w') {

            // choose a piece
            if (this.#choosePiece(position)) {
                this.click_sound.play();
            }

            // continue or start a move
            if (this.#isMoveInProgress()
                || (!this.#choosePiece(position) && this.#isPieceChosen())) {
                this.click_sound.play();
                this.#movePiece(position);
            }
        }
    }

    /**
     * Handles a undo button click.
     * If there was a state previous to the current, pops it out of the history,
     * initialize the move coordinator with it and sets it as the current state.
     */
    handleUndoClick() {
        if (this.history.length > 0) {
            var previousState = this.history.pop();
            this.setState(previousState);
        }
    }

    /**
     * Handles bot change by setting selected bot in state.
     */
    handleBotChange(selectedBot){
        this.setState({chosenBot: selectedBot});
    }

    renderBoard() {
        return (
            <Board board={this.state.board}
                   handleClick={this.handleSquareClick}
                   chosenPiece={this.state.chosenPiece}
                   availableSquares={this.getAvailableSquares()}
                   pathTravelled={this.state.pathTravelled}
                   availableStarts={this.state.availableStarts}/>
        );
    }

    render() {
        return (
            <div className="game">
                <div className="game-board">
                    {this.renderBoard()}
                </div>
                <InfoPanel 
                    handleUndoClick={this.handleUndoClick}
                    currentPlayer={this.state.activePlayer}
                    handleBotChange={(e) => this.handleBotChange(e.target.value)}
                />
            </div>
        );
    }
}