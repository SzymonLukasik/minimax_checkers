import React from 'react';

const BotSelector = (props) => {
    // Dropdown menu for bot selection
    // Available options: First possible, Random
    return (
        <div className="bot-selector">
            <select onChange={(e) => props.handleBotChange(e)} >
                <option value="bot_random" className="bot-easy">
                    Random Move (Easy)
                </option>
                <option value="bot_first_possible" className="bot-medium">
                    First Possible Move (Medium)
                </option>
                <option value="bot_minimax" className="bot-hard">
                    Minimax (Hard) 
                </option>
                <option value="bot_minimax_hard" className="bot-hard">
                    Minimax hard (Very Hard)
                </option>

            </select>
        </div>
    );
}

export default BotSelector;
