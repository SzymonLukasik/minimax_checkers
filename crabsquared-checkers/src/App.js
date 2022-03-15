import React, { useState, useEffect } from 'react';
import './style/App.css';

function App() {
  const [testVar, setTestVar] = useState(0);

  useEffect(() => {
    fetch('/available_moves', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({
        'type': 'board',
        'state': [
          ['b', '.', 'b', '.', 'b', '.', 'b', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', '.', '.', '.', '.', '.', '.', '.'],
          ['.', 'w', '.', 'w', '.', 'w', '.', 'w']
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
          {testVar.type}
        </p>
    </div>
  );
  
}

export default App;
