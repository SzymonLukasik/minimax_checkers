import React, { useState, useEffect, useRef } from 'react';
import './Board.css';

import Square from '../Square/Square';

class Board extends React.Component {
    renderRow(i) {
        return (
            <div className="board-row" key={i}>
                {this.props.board[i].map((el, index) => (
                   <Square value={el} x={i} y={index} 
                           onClick={() => this.props.handleClick(i, index)}
                           key={i + index}/>
                ))}
            </div>
        );
    }

    renderBoard() {
        return (
            <div className="board-row">
                {this.props.board.map((el, index) => (
                    this.renderRow(index)
                ))}
            </div>
        );
    }

    render() {
        return (
            <div className="board">
                
                <div>
                {this.renderBoard()}
                </div>
            </div>
        );
    }
}

export default Board;
