import React from 'react';
import './Square.scss';

class Square extends React.Component {

    #getClassName() {
        return (
            (this.props.position.isPlayable() === true)
            ? (
                (this.props.chosen === true)
                ? 'square-chosen'
                : (this.props.availableStart === true)
                ? 'square-start'
                : (
                    (this.props.available === true)
                    ? 'square-available'
                    : (
                        (this.props.travelled === true)
                        ? 'square-travelled'
                        : 'square-playable'
                    )
                )
            )
            : 'square-idle'
        );
    }

    renderPiece() {
        return (
            <div>
                {
                    (this.props.value === 'w')
                    ? <img src="/bialy_pion.svg" alt='w' />
                    : (this.props.value === 'b')
                    ? <img src="/czarny_pion.svg" alt='b' />
                    : (this.props.value === 'W')
                    ? <img src="/bialy_krol.svg" alt='W' />
                    : (this.props.value === 'B')
                    ? <img src="/czarny_krol.svg" alt='B' />
                    : ''
                }
            </div>
            
        );
    }

    render() {
        return (
            <button className={this.#getClassName()} 
                    onClick={() => this.props.onClick(this.props.position)}>
                <div>
                    { this.renderPiece() }
                </div>

            </button>
        );
    }
}

export default Square;