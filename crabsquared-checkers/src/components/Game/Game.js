import React from 'react';
import { cloneDeep } from 'lodash';
import './Game.css';

import Board from '../Board/Board';
import InfoPanel from '../InfoPanel/InfoPanel';
import Move from './Move';
import { Position } from './Position';

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

            /** Position of a piece to be moved. */
            chosenPiece: null,

            /** List of paths that describes possible moves for a chosen piece. */
            availablePaths: null,

            /** Path of squares travelled by currently chosenPiece */
            pathTravelled: []
        }
        this.handleSquareClick = this.handleSquareClick.bind(this);
        this.handleUndoClick = this.handleUndoClick.bind(this);

        /** Contains all game states previous to the current one. */
        this.history = [];

        /** Helps handle moves. */
        this.move = new Move(this);

        this.click_sound = new Audio('/click.wav');

        this.error_sound = new Audio('/error.wav');

        this.bot_sound = new Audio('/bot_move.wav');
    }

    getBoard() {
        return this.state.board;
    }

    getActivePlayer() {
        return this.state.activePlayer;
    }

    getChosenPiece() {
        return this.state.chosenPiece;
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

    /**
     * Handles a choose of a piece.
     * @param {*} position - clicked position
     * @returns whether a piece was choosen successfully
     */
    #choosePiece(position) {
        if (this.state.board.atPosition(position) === this.state.activePlayer) {
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
     * Convert received two letter e.g. 'B3' string to Position (1, 2)
     * @param {*} positionString - string of form 'B3'
     * @returns Position
     */
    convertStringToPosition(string) {
        return new Position(string.charCodeAt(1) - 49, string.charCodeAt(0) - 65);
    }

    /**
     * Translate bot move to Position list
     * @param {*} receivedMove - bot move in form of array of strings 
     * @returns Position list
     */
    translateBotMove(receivedMove) {
        return receivedMove.map(move => this.convertStringToPosition(move));
    }


    /**
     * Converts state.board to array of strings supported by API (swaps 'b' and 'w' characters).
     */
    convertStateToSend() {
        const boardToSend = this.state.board.map(row =>
            row.map(piece => piece === 'b' ? 'w' : (piece === 'w' ? 'b' : piece)));
        return boardToSend;
    }

    /**
     * Fetches a bot move from the server and performs it.
     */
    performBotMove = async () => {
        fetch('/bot_move', {
            method: 'POST',
            headers: { 'Content-Type': 'application/json' },
            body: JSON.stringify({
              'type': 'board',
              'state': this.convertStateToSend()
            })
        }).then(response => response.json()).then(data => {
            console.log(data.move);
            var moves = this.translateBotMove(data.move);
            console.log(moves);
            
            // perform each by choose and jump
            for(var i = 0; i < moves.length - 1; i++) {
                this.#choosePiece(moves[i]);
                setTimeout(function(targetMove) {
                    console.log(moves[i+1]);
                    this.bot_sound.play();
                    this.setState(this.move.jumpOn(targetMove));
                }.bind(this), 500, moves[i+1]);
            }
        })
    }

    /**
     * Check if it's a bot's turn and perform a bot move if it is.
     */
    componentDidUpdate() {
        if (this.state.activePlayer === 'b' && !this.#isPieceChosen()) {
            this.performBotMove();
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
        // play sound effect 
        if (this.#choosePiece(position)) {
            this.click_sound.play();
        }

        if (this.#isMoveInProgress() || this.state.activePlayer === 'b'
            || (!this.#choosePiece(position) && this.#isPieceChosen())){
            this.click_sound.play();
            this.#movePiece(position);
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

    renderBoard() {
        return (
            <Board board={this.state.board}
                   handleClick={this.handleSquareClick}
                   chosenPiece={this.state.chosenPiece}
                   availableSquares={this.getAvailableSquares()}
                   pathTravelled={this.state.pathTravelled}/>
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
                />
            </div>
        );
    }
}