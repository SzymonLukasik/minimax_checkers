import React, { useState, useEffect, useRef } from 'react';
import './Game.css';

import Board from '../Board/Board';

class Game extends React.Component {
    constructor(props){
        console.log('siema tu plansza');

        super(props);
        this.state = {
            board: [
                ['c','-','c','-','c','-','c','-'],
                ['-','c','-','c','-','c','-','c'],
                ['c','-','c','-','c','-','c','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','-','-','-','-','-','-','-'],
                ['-','b','-','b','-','b','-','b'],
                ['b','-','b','-','b','-','b','-'],
                ['-','b','-','b','-','b','-','b']
            ],
            activePlayer: 'b',
            count: 0,
        }
        this.handleClick = this.handleClick.bind(this);
    }

    handleClick(i,j) {
        console.log('click');
        console.log(this.state.board);
        const squares = this.state.board.slice();
        squares[i][j] = this.state.activePlayer;
        this.setState({
            squares: squares,
            activePlayer: this.state.activePlayer == 'b' ? 'c' : 'b',
            count: this.state.count + 1,
        });
    }

    renderBoard() {
        return (
            <Board board={this.state.board} handleClick={this.handleClick}/>
        );
    }

    render() {
        return (
            <div className="game">
                <div className="game-board">
                    {this.renderBoard()}
                </div>
            </div>
            
        );
    }
}

export default Game;
