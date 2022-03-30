import React from 'react';
import './App.css';

import Game from './components/Game/Game';
import Title from './components/Title/Title';

function App() {
  /*
  const [currentTime, setCurrentTime] = useState(0);

  useEffect(() => {
    fetch('/bot_move', {
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
  */

  return (
    <div className="App">
      <Title />        
      <Game />
    </div>
  );
  
}

export default App;
