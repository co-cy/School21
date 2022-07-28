import React, {useRef} from 'react'
import '../App.css';
import {
    BrowserRouter as Router,
    Routes,
    Route,
    Link
  } from "react-router-dom";
import Login from './Login'
  
export default function RegistrationCompany() {
    

    const in_company_name = useRef();
    const in_login = useRef();
    const in_password = useRef();
    const password_repeat = useRef();
    return (
        <div className="Login">
            <div style={{border: "8px double black", backgroundColor: "rgba(16, 19, 20, 80%)", padding: "10px 30px 10px 30px"}}>
                <p><input ref={in_company_name} placeholder="Company name"></input></p>
                <p><input ref={in_login} placeholder="Login"></input></p>
                <p><input ref={in_password} placeholder="Password"></input></p>
                <p><input ref={password_repeat} placeholder="Repeat password"></input></p>
                <p style={{color: "#a19191"}}>Already have an account? <a href="/login">Sign in</a></p>
                <p style={{display: 'flex', justifyContent: "flex-end", position: "relative", right: "1%"}}><button >Sign up</button></p>
            </div>
        </div>
    )
}
