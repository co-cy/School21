import React, {useEffect, useState} from 'react'
import '../App.css';
import {useParams} from "react-router-dom";

export default function Vacancy() {
    const params = useParams();
    const [vacancy, setVacancy] = useState([]);

    useEffect(() => {
        fetch("http://localhost:3000/vacancies/" + params.id, {
            method: 'GET',
            headers: {
                Accept: "application/json",
            'Content-Type': 'application/json;charset=utf-8'
            },
        }).then(response => response.json().then(res => {setVacancy(res)}));
    }, [params.id])

    return (
        <div style={{color: "#fff", display: "grid", gridTemplateColumns: "repeat(4, 1fr)", gridTemplateRows: "repeat(5, 1fr)"}}>
            <div className="vacancy" style={{gridColumn: "1/3", alignSelf: "center", overflow: "hidden", height: "45%", margin: "5%"}}><span>{vacancy.title}</span></div>
            <div style={{gridColumn: "3/3", alignSelf: "center"}}><span className="vacancy">English lvl: {vacancy.english}</span></div>
            <div style={{gridColumn: "4/4", alignSelf: "center"}}><span className="vacancy">Grade: {vacancy.grade}</span></div>
            <div className="vacancy" style={{gridColumn: "1/3",gridRow: "2/4", alignSelf: "center", overflow: "hidden", height: "85%", marginLeft: "5%", marginRight: "5%"}}><span >{vacancy.description}</span></div>  
        </div>
    )
}
