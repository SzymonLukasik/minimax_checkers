import React, { useState, useEffect } from 'react';
import './style/App.css';

function App() {
  const [testVar, setTestVar] = useState(0);

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
    .then(data => { setTestVar(data); });
  }, []);

  return (
    <div className="App">        
        <p>
          🦀 CrabSquared Rulez 🦀
        </p>
        <p>
          {JSON.stringify(testVar, null, 2)}
        </p>
    </div>
  );
  
}

export default App;
