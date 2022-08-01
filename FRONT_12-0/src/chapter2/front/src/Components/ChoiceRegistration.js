import React from 'react'
import '../App.css';
import {Link} from "react-router-dom";

export default function ChoiceRegistration() {

    return (
        <div className="Login">
            <div style={{border: "8px double black", backgroundColor: "rgba(16, 19, 20, 80%)", padding: "40px 40px 30px 40px"}}>
            <p><Link to="/signup"><button>User</button></Link></p>
            <p><Link to="/company-signup"><button>Company</button></Link></p>
            </div>
        </div>
    )
}
