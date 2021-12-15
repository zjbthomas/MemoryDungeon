import { Route } from 'react-router';

/**
 * Import all page components here
 */
import LoginPage from './components/LoginPage';
import MainPage from './components/MainPage';

/**
 * All routes go here.
 * Don't forget to import the components above after adding new route.
 */
export default (
  <Route>
    <Route exact path="/" component={LoginPage} />
    <Route path="/main" component={MainPage} />
  </Route>
);