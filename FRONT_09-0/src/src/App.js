import {useState, useEffect, useRef, useCallback} from "react";
import ThemeContext from "./context"


import PokemonList from "./component/pokemonList";

function findPokemon(pokemon, curPokemonName) {
    let tmp = curPokemonName.toLowerCase();
    return pokemon.find(onePokemon => onePokemon.name.toLowerCase() === tmp);
}

function App() {
    const [pokemon, setPokemon] = useState([]);
    const [find, setFind] = useState(null);
    const [addedPokemon, setAddedPokemon] = useState([]);
    const [isLight, setIsLight] = useState(true);

    const inputText = useRef();
    console.log("APP RENDER");

    useEffect(() => {
        let res = localStorage.getItem("pokemon")
        if (res) {
            setPokemon(JSON.parse(res))
        } else {
            fetch("https://pokeapi.co/api/v2/pokemon")
                .then(res => res.json())
                .then(res => res.results)
                .then(async (res) => {
                    let list_pokemon = [];
                    for (let one_pokemon of res) {
                        await fetch(one_pokemon.url)
                            .then(res2 => res2.json())
                            .then(res2 => {
                                one_pokemon["info"] = res2;
                                list_pokemon.push(one_pokemon)
                            })
                    }
                    setPokemon(list_pokemon);
                    localStorage.setItem("pokemon", JSON.stringify(list_pokemon));

                })
        }
    }, [])

    const deletePokemon = useCallback((index) => {
        let a = [...addedPokemon];
        a.splice(index, 1);
        setAddedPokemon(a);
        setFind(null);
    }, [addedPokemon]);

    const aboba = useCallback(() => {
        let resFind = findPokemon(pokemon, inputText.current.value);
        if (resFind !== find) {
            if (resFind)
                setAddedPokemon([resFind, ...addedPokemon]);
            setFind(resFind);
        }
        }, [pokemon, find, addedPokemon]);

    return (
        <div className={isLight ? "app" : "app-dark"} style={{height: "100vh"}}>
            <div style={{position: "relative", display: "flex", justifyContent: "right", right: "3%", top: "3%"}}>
                <div className="box-2">
                    <input type='checkbox' onClick={() => setIsLight(!isLight)} defaultChecked={!isLight}/>
                    <span className="toogle"></span>
                </div>
            </div>
            <div style={{margin: "auto"}}>
                <input ref={inputText} placeholder="Введите покемона"/>
                <button onClick={aboba}>Найти</button>
            </div>
            <p>{(find === null? "": (find? "Найден" : "Не найден"))}</p>

            < ThemeContext.Provider value={isLight}>
                <PokemonList pokemon={addedPokemon} deletePokemon={deletePokemon}/>
            </ ThemeContext.Provider>
        </div>
    );
}

export default App;
