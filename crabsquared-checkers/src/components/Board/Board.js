import React from 'react';
import './Board.css';

import Square from '../Square/Square';
import { Position } from '../Game/Position';

class Board extends React.Component {
    
    isSquareAvailable(i, j) {
        return (
            this.props.availableSquares
            && this.props.availableSquares.some((pos) =>  Position.areEqual(pos, [i, j]))
        );
    }

    renderRow(row, i) {
        return (
            <div className="board-row" key={i}>
                {row.map((el, j) => (
                   <Square value={el} position={new Position(i, j)}
                           chosen={Position.areEqual(this.props.chosenPiece, [i, j])}
                           available={this.isSquareAvailable(i, j)}
                           onClick={this.props.handleClick}
                           key={j}/>
                ))}
            </div>
        );
    }

    renderBoard() {
        return (
            <div className="board-row">
                {this.props.board.map((row, i) => (this.renderRow(row, i)))}
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
