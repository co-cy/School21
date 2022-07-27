import { createStore } from 'redux';

const ADD = "ADD";
const REMOVE = "REMOVE";


function addPokemon(newPokemon) {
    return {
        type: ADD,
        value: newPokemon
    };
}

function removePokemon(index) {
    return {
        type: REMOVE,
        index: index
    };
}


function reducer(state, action) {
    function add(pokemon) {
        return [pokemon, ...state.value]
    }

    function remove(index) {
        let a = [...state.value];
        a.splice(index, 1);
        return a;
    }

    switch(action.type) {
        case ADD: return { value: add(action.value) };
        case REMOVE: return { value: remove(action.index) };
        default: return state;
    }
}


const pokemonStorage = createStore(reducer, {value: []});

const all = { pokemonStorage, ADD, REMOVE, addPokemon, removePokemon };

export default all
