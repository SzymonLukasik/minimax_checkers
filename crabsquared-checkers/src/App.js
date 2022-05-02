import React from 'react';
import { useState, useEffect } from 'react';
import './App.css';

import Game from './components/Game/Game';
import Title from './components/Title/Title';

function App() {
  
  // Test Request
  useEffect(() => {
    fetch('/bot_move', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        'type': 'board',
        'state': [
          ['.','b','.','b','.','.','.'],
          ['.','.','.','.','.','.','.'],
          ['.','b','.','b','.','.','.'],
          ['.','.','W','.','.','.','.'],
          ['.','.','.','.','.','.','.'],
          ['.','.','.','.','.','.','.'],
          ['.','.','.','.','.','.','.'],
      ]
      })
    })
    .then(res => res.json())
    .then(data => { console.log(data) });
  }, []);
  

  return (
    <div className="App">
      <Title />        
      <Game />
    </div>
  );
  
}

export default App;
