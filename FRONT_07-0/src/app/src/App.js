import {useEffect, useState} from "react";

function Time(prop) {
    return (
        <p>{Math.round(prop.time / 3600)}:{Math.round(prop.time / 60) % 60}:{prop.time % 60}</p>
    )
}


function SomeList(props) {
    return  (
        <div>
            {props.items.map((time) => (
                <Time time={time}/>
            ))}
        </div>
    )
}

function Timer() {
  const [time, setTime] = useState(0);
  const [isActive, setActive] = useState(false);
  const [listFreeze, setList] = useState([]);

  useEffect(() => {
      if (isActive) {
          const timer = setTimeout(() => setTime(time + 1), 1000);
          return () => clearTimeout(timer);
      }
  }, [isActive, time]);

  useEffect(() => {
      console.log(listFreeze);
  }, [listFreeze]);

  return (
      <div className="App">
          <Time time={time}/>
          <button onClick={() => setActive(!isActive)}>{!isActive? "ON":"OFF"}</button>
          <button onClick={() => {setTime(0); setList([])}}>Clear</button>
          <button onClick={() => setList(listFreeze.concat([time]))}>Add</button>
          <SomeList items={listFreeze}/>
      </div>
  );
}

function AboutMe() {
  return (
        <div>
            <img alt="My face" width="10%" src="i.png"/>
            <p>Fedorov Stepan Nik</p>
            <p>Age: ...</p>
        </div>
  )
}

function App() {
    const [state, setState] = useState(0);

    return (
      <div>
          <button onClick={() => setState(0)}>StudentInfo</button>
          <button onClick={() => setState(1)}>Timer</button>

          {state? <Timer/> : <AboutMe/>}

      </div>
  )

}

export default App;
