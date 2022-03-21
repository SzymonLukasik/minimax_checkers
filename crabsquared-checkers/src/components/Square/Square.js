import React from 'react';
import './Square.scss';

class Square extends React.Component {

    getClassName() {
        return (
            (this.props.position.playable() === true)
            ? (
                (this.props.chosen === true)
                ? 'square-chosen'
                : (
                    (this.props.available === true)
                    ? 'square-available'
                    : 'square-playable'
                )
            )
            : 'square-idle'
        );
    }

    render() {
        return (
            <button className={this.getClassName()} 
                    onClick={() => this.props.onClick(this.props.position)}>
                <div>
                    {
                        (this.props.value === 'b')
                        ? '🦀'
                        : (this.props.value === 'c')
                        ? '🕷️' 
                        : ''
                    }
                </div>

            </button>
        );
    }
}

export default Square;