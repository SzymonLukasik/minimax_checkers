import React, { useState, useEffect } from 'react';
import './style/App.css';

function App() {
  const [currentTime, setCurrentTime] = useState(0);

  useEffect(() => {
    fetch('/time').then(res => res.json()).then(data => {
      setCurrentTime(data.time);
    });
  }, []);

  return (
    <div className="App">        
        <p>
          🦀 CrabSquared Rulez 🦀
        </p>
        <p>
          The current time is {currentTime}.
        </p>
    </div>
  );
  
}

export default App;
