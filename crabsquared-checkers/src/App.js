import React from 'react';
import './App.css';

import Game from './components/Game/Game';
import Title from './components/Title/Title';

function App() {
  /*
  const [currentTime, setCurrentTime] = useState(0);

  useEffect(() => {
    fetch('/time').then(res => res.json()).then(data => {
      setCurrentTime(data.time);
    });
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
