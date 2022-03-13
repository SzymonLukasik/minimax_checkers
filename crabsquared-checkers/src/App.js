import React, { useState, useEffect } from 'react';
import './style/App.css';

function App() {
  const [testVar, setTestVar] = useState(0);

  useEffect(() => {
    fetch('/test', {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({'var': 7})
    })
    .then(res => res.json())
    .then(data => { setTestVar(data.var); });
  }, []);

  return (
    <div className="App">        
        <p>
          🦀 CrabSquared Rulez 🦀
        </p>
        <p>
          7 + 1 = {testVar}
        </p>
    </div>
  );
  
}

export default App;
