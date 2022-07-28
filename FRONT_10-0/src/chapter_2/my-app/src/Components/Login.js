import React, {useRef, useState} from 'react'
import '../App.css';
import {
    BrowserRouter as Router,
    Routes,
    Route,
    Link
  } from "react-router-dom";
import Registration from './Registration'

export default function Login() {
    const [log_succes, setLogin] = useState({find : null});
    const login = React.useCallback(() => {
        console.log(JSON.stringify({login: in_login.current.value, password: in_password.current.value}));
        fetch("http://localhost:3000/login", {
            method: 'POST',
            headers: {
                Accept: "application/json",
            'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify({login: in_login.current.value, password: in_password.current.value})
        }).then(response => response.json().then(res => {console.log(res); setLogin(res)}));
    }, [])

    const in_login = useRef();
    const in_password = useRef();
    return (
        <div style={{border: "8px double black", backgroundColor: "rgba(16, 19, 20, 80%)", padding: "30px 20px 10px 20px"}}>
            <p><input  ref={in_login} placeholder="Login"></input></p>
            <p><input ref={in_password} placeholder="Password"></input></p>
            <p style={{color: "#a19191"}}>New to BestVacancies? <Link to="/signup">Create an account</Link></p>
            <p onClick={login} style={{display: 'flex', justifyContent: "flex-end", position: "relative", right: "1%"}}><button >Sign in</button></p>
            {log_succes.find === true ? <p>Found</p> : (log_succes.find === false ? <p>Not found</p> : "")}
        </div>
    )
}
