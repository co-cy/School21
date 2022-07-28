import './App.css';
import Login from './Components/Login';
import Registration from './Components/Registration'
import RegistrationCompany from './Components/RegistrationCompany'
import {
  BrowserRouter as Router,
  Routes,
  Route,
  Link
} from "react-router-dom";

function App() {
  return (
    <div className="App">
        <Router>
          <div className="Login">
              <Routes>
                  <Route path="/login" element={<Login/>} />
                  <Route path="/signup" element={<Registration/>}/>
              </Routes>
          </div>
        </Router>

    </div>
  );
}

export default App;
