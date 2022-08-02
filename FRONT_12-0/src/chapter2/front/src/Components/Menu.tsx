import React from 'react'
import '../App.css';
import {Link} from "react-router-dom";
import {TbNotes} from 'react-icons/tb'
import {GoTasklist} from 'react-icons/go'
import {MdLogout} from 'react-icons/md'
import {MdCreate} from 'react-icons/md'

export default function Menu(props: any) {

    return (
        <div className="Menu">
            <div className="vertical-menu">
                <div >
                    <Link to="/vacancies">
                        <p style={{padding: "30% 0 15px 0"}}><TbNotes style={{transform: "scale(4)", color: "rgb(150 130 176)"}}/></p>
                        <p>Vacancies</p>
                    </Link>
                    <Link to="/my-vacancies">
                        <p style={{padding: "30% 0 15px 0"}}><GoTasklist style={{transform: "scale(3.7)", color: "rgb(150 130 176)"}}/></p>
                        <p>My vacancie</p>
                    </Link>
                    <Link to="/create-vacancy">
                        <p style={{padding: "30% 0 15px 0"}}><MdCreate style={{transform: "scale(3.2)", color: "rgb(150 130 176)"}}/></p>
                        <p>Create vacancy</p>
                    </Link>
                </div>

                <div style={{position: "relative", top: "60%", justifyContent: "center"}}>
                    <Link to="/login">
                        <p><MdLogout style={{transform: "scale(3.7)", color: "rgb(150 130 176)"}}/></p>
                        <p>Logout</p>
                    </Link>
                </div>
            </div>
            {props.children}
        </div>
    )
}
