import './App.css';
import Login from './Components/Login';
import Registration from './Components/Registration'
import RegistrationCompany from './Components/RegistrationCompany'
import ChoiceRegistration from './Components/ChoiceRegistration'
import Menu from './Components/Menu'
import Vacancies from './Components/Vacancies';
import Vacancy from './Components/Vacancy';
import CreateVacancy from './Components/CreateVacancy';

import {
  BrowserRouter as Router,
  Routes,
  Route
} from "react-router-dom";

function App() {
  return (
    <div className="App">
        <Router>
              <Routes>
                  <Route path="/login" element={<Login/>} />
                  <Route path="/signup" element={<Registration/>}/>
                  <Route path="/company-signup" element={<RegistrationCompany/>}/>
                  <Route path="/choice" element={<ChoiceRegistration/>}/>
                  <Route path="/vacancies" element={<div><Menu><Vacancies/></Menu></div>}/>
                  <Route path="/my-vacancies" element={<div><Menu/><ChoiceRegistration/></div>}/>
                  <Route path="/vacancies/:id" element={<div><Menu><Vacancy/></Menu></div>}/>
                  <Route path="/create-vacancy" element={<div><Menu><CreateVacancy/></Menu></div>}/>
              </Routes>
        </Router>

    </div>
  );
}

export default App;
