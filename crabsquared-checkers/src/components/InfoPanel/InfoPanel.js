import React from 'react';
import './InfoPanel.scss';
import BotSelector from './BotSelector/BotSelector'

const InfoPanel = ({handleUndoClick, currentPlayer, handleBotChange}) => {
    return (
        <div className="info-panel">
            <div className='info-item'>
                Current Player:  
                {
                    (currentPlayer === 'w')
                    ? '🦀'
                    : '🕷️'
                }
            </div>
            <button className="undo-button"
                onClick={handleUndoClick}>
            </button>
            <div className='info-item'>
                <BotSelector handleBotChange={handleBotChange}/>
            </div>
        </div>
    );
}

export default InfoPanel;
