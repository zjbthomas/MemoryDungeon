import ReactDOM from 'react-dom'

import App from './components/App';

/** Firebase */
// Import the functions you need from the SDKs you need
import { initializeApp } from "firebase/app";
import { getAnalytics } from "firebase/analytics";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
// For Firebase JS SDK v7.20.0 and later, measurementId is optional
const firebaseConfig = {
  apiKey: "AIzaSyANz8lzKcGwqrvEKl-RbKi75TpO0pFPmro",
  authDomain: "memorydungeon.firebaseapp.com",
  projectId: "memorydungeon",
  storageBucket: "memorydungeon.appspot.com",
  messagingSenderId: "106951401468",
  appId: "1:106951401468:web:86ff30278eecad686c5c79",
  measurementId: "G-2TND4FPMGY"
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const analytics = getAnalytics(app);

ReactDOM.render(
  <App />,
  window.document.getElementById('container')
);