import React, {useEffect, useState} from 'react'
import '../App.css';
import {Link} from "react-router-dom";

export default function Vacancies() {
    const [vacancies, setVacancies] = useState([]);

    useEffect(() => {
        fetch("http://localhost:3000/vacancies", {
            method: 'GET',
            headers: {
                Accept: "application/json",
                'Content-Type': 'application/json;charset=utf-8'
            },
        }).then(response => response.json().then(res => {setVacancies(res)}));
    }, [])

    return (
        <div style={{}}>
            {vacancies.map(({id, title, description}, index) => (
                <Link key={index} to={"/vacancies/" + id} style={{textDecoration: "none"}}>
                    <div className="vacan">
                        <div style={{textAlign: "left", marginLeft: "5%", fontSize: "20px"}}>{title}</div>
                        <p>{description}</p>
                    </div>
                </Link>
            ))}
        </div>
    )
}
