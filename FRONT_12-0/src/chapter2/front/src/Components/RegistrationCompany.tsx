import React, {useRef, useState} from 'react'
import '../App.css';
import {Link, Navigate} from "react-router-dom";

export default function RegistrationCompany() {
    const [match, setMatch] = useState<boolean>(true);
    const [log_succes, setLogin] = useState({status : null});

    const in_company_name = useRef<HTMLInputElement>(null);
    const in_login = useRef<HTMLInputElement>(null);
    const in_password = useRef<HTMLInputElement>(null);
    const password_repeat = useRef<HTMLInputElement>(null);

    const registration = React.useCallback(() => {
        if (in_password.current != null && password_repeat.current != null) {
            let is_match = in_password.current.value === password_repeat.current.value
            setMatch(is_match);
            if (is_match) {
                fetch("http://localhost:3000/company-signup", {
                    method: 'POST',
                    headers: {
                        Accept: "application/json",
                        'Content-Type': 'application/json;charset=utf-8'
                    },
                    body: JSON.stringify({
                        login: in_login.current? in_login.current.value : undefined,
                        password: in_password.current.value})
                }).then(response => response.json().then(res => {
                    setLogin(res)
                }));
            }
        }
    }, [])

    return (
        <div className="Login">
            <div style={{border: "8px double black", backgroundColor: "rgba(16, 19, 20, 80%)", padding: "10px 30px 10px 30px"}}>
                <p><input ref={in_company_name} placeholder="Company name"></input></p>
                <p><input ref={in_login} placeholder="Login"></input></p>
                <p><input type="password" ref={in_password} placeholder="Password"></input></p>
                <p><input type="password" ref={password_repeat} placeholder="Repeat password"></input></p>
                {!match ? <p>Passwords do not match</p> : ""}
                <p style={{color: "#a19191"}}>Already have an account? <Link to="/login">Sign in</Link></p>
                <p onClick={registration} style={{display: 'flex', justifyContent: "flex-end", position: "relative", right: "1%"}}><button >Sign up</button></p>
                {log_succes.status === true ? <Navigate to="/login" /> : (log_succes.status === false ? <p>Error</p> : "")}
            </div>
        </div>
    )
}
