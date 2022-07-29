import React, {useRef, useState} from 'react'
import '../App.css';
import { Navigate} from "react-router-dom";

export default function CreateVacancy() {
    const [close, setClose] = useState(0);
    const [create_succes, setCreate] = useState({status : null});
    const title = useRef();
    const description = useRef();
    const lvl = useRef();
    const grade = useRef();

    const create_vacancy = React.useCallback(() => {
        fetch("http://localhost:3000/create-vacancy", {
            method: 'POST',
            headers: {
                Accept: "application/json",
            'Content-Type': 'application/json;charset=utf-8'
            },
            body: JSON.stringify({title: title.current.value, description: description.current.value, english: lvl.current.value, grade: grade.current.value})
        }).then(response => response.json().then(res => {setCreate(res)}));
    }, [])

    return (
        <div className="create">
            <div style={{gridColumn: "2/4", gridRow: "2/3", alignSelf: "center"}}>
                <p><input ref={title} placeholder="Vacancy title" style={{overflow: "hidden",  width: "100%", height: "80px"}}></input></p>
            </div>
            <div style={{gridColumn: "2/4", gridRow: "3/4", alignSelf: "center"}}>
                <p><input ref={description} placeholder="Vacancy description" style={{overflow: "hidden", width: "100%", height: "200px"}}></input></p>
            </div>
            <form style={{gridColumn: "2/3", gridRow: "4/4", justifySelf: "start", overflow: "hidden", width: "100%", textAlign: "left", paddingTop: "5%"}}>
                <span>English lvl</span>
                <select ref={lvl} name="en_lvl" style={{overflow: "hidden", width: "100%", height: "35px"}}>
                    <option value="A0">A0</option>
                    <option value="A1">A1</option>
                    <option value="A2">A2</option>
                    <option value="B1">B1</option>
                    <option value="B2">B2</option>
                    <option value="C1">C1</option>
                    <option value="C2">C2</option>
                </select>
            </form>
            <form style={{gridColumn: "2/3", gridRow: "5/5", justifySelf: "start", overflow: "hidden", width: "100%", textAlign: "left", paddingTop: "5%"}}>
                <span>Grade</span>
                <select ref={grade} name="grade" style={{overflow: "hidden", width: "100%", height: "35px"}}>
                    <option value="1">1</option>
                    <option value="2">2</option>
                    <option value="3">3</option>
                    <option value="4">4</option>
                    <option value="5">5</option>
                </select>
            </form>
            <div style={{gridColumn: "4/5", gridRow: "7/8"}}>
                <p><button onClick={() => {setClose(1)}} style={{overflow: "hidden", width: "80%", height: "25px"}}>Close</button></p>
            </div>
            <div style={{gridColumn: "5/6", gridRow: "7/8"}}>
                <p><button onClick={create_vacancy} style={{overflow: "hidden", width: "80%", height: "25px"}}>Save</button></p>
            </div>

            {close === 1 || create_succes.status === true ? <Navigate to="/vacancies" /> : ""}
        </div>
        
    )
}
