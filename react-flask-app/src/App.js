import React, { useState, useEffect } from 'react';
import './App.css';

function App() {
  const [currentTime, setCurrentTime] = useState(0);
  const [nextMove, setNextMove] = useState(0);

  useEffect(() => {
    fetch('/time').then(res => res.json()).then(data => {
      setCurrentTime(data.time);
    });
  }, []);

  useEffect(() => {
    fetch('/move').then(res => res.json()).then(data => {
      setNextMove(data.move);
    });
  }, []);

  if (nextMove == 0){
    return (
      <div className="App">
        <header className="App-header">
          <p>
            🦀 CrabSquared Rulez 🦀
          </p>
          <p>The current time is {currentTime}.</p>
          <p>Waiting for kickass model to get next move...</p>
        </header>
      </div>
    );
  } else {
    return (
      <div className="App">
        <header className="App-header">
          <p>
            🦀 CrabSquared Rulez 🦀
          </p>
          <p>The current time is {currentTime}.</p>
          <p>The next move is {nextMove}.</p>
        </header>
      </div>
    );
  }
  
}

export default App;
