import React from 'react';
import './Board.css';

import Square from '../Square/Square';
import { Position } from '../Game/Position';

class Board extends React.Component {
    
    #renderRow(row, i) {
        return (
            <div className="board-row" key={i}>
                {row.map((el, j) => (
                   <Square value={el} position={new Position(i, j)}
                           chosen={Position.areEqual(this.props.chosenPiece, [i, j])}
                           available={this.props.availableSquares.some((pos) =>  Position.areEqual(pos, [i, j]))}
                           onClick={this.props.handleClick}
                           travelled={this.props.pathTravelled.some((pos) => Position.areEqual(pos, [i, j]))}
                           availableStart={this.props.availableStarts.some((pos) => Position.areEqual(pos, [i, j]))}
                           key={j}/>
                ))}
            </div>
        );
    }

    #renderBoard() {
        return (
            <div className="board-row">
                {this.props.board.map((row, i) => (this.#renderRow(row, i)))}
            </div>
        );
    }

    render() {
        return (
            <div className="board">
                <div>
                    {this.#renderBoard()}
                </div>
            </div>
        );
    }
}

export default Board;
