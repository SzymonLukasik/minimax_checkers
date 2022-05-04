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
                    (currentPlayer === 'w')
                    ? <img src="/bialy_pion.svg" alt='w' />
                    : <img src="/czarny_pion.svg" alt='w' />
                }
            </div>
            <button className="undo-button"
                onClick={handleUndoClick}>
            </button>   
        </div>
    );
}

export default InfoPanel;
