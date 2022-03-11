import React, { useState, useEffect, useRef } from 'react';
import './Square.scss';

class Square extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            piece: this.props.value === '-' ? '' : this.props.value,
            playable: ((this.props.x + this.props.y) % 2 === 0) ? true : false,
        }
    }

    render() {
        return (
            <button className={this.state.playable === true ? 'square-playable' : 'square-idle'} 
                    onClick={() => this.props.onClick} >
                <div>
                    {this.state.piece === 'b' ? '🦀' : ''}
                    {this.state.piece === 'c' ? '🕷️' : ''}
                </div>

            </button>
        );
    }
}

export default Square;