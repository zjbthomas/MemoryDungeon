
import React from 'react';
import { Route, Router } from 'react-router';

import LoginPage from './LoginPage';
import MainPage from './MainPage';

class App extends React.Component {
    render() {
      return (
        <Router>
            <div>
            <Route exact path="/" component={LoginPage} />
            <Route path="/main" component={MainPage} />
            </div>
        </Router>
    );
    }
  }

export default App;