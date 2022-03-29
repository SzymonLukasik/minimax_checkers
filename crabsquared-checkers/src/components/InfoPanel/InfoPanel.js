import React from 'react';
import './InfoPanel.scss';

const InfoPanel = ({handleUndoClick, currentPlayer}) => {
    return (
        <div className="info-panel">
            <div className='info-item'>
                MIM UW 2022
            </div>
            <div className='info-item'>
                Current Player:  
                {
                    (currentPlayer === 'b')
                    ? '🦀'
                    : '🕷️'
                }
            </div>
            <button className="undo-button"
                onClick={handleUndoClick}>
            </button>   
        </div>
    );
}

export default InfoPanel;
