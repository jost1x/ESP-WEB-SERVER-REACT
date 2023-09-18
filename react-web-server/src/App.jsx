import { useState } from 'react'
import "normalize.css"
import "mini.css"
import Header from './components/Header/Header'
import { Routes, Route } from "react-router-dom";
import Footer from './components/Footer/Footer';
import Index from './Content/Index';
import Settings from './Content/Settings';
import NotFound from './Content/NotFound';


function App() {


  return (
    <div className="container">

      <Header />

      <div id="row">
        <div className="col">
          <h3>
            {import.meta.env.VITE_DEVICE_ID}
            <small>{import.meta.env.VITE_SITE_NAME}</small>
          </h3>
          <Routes>
            <Route path="/" element={<Index />} />
            <Route path="/settings" element={<Settings />} />
            <Route path="*" element={<NotFound/>} />
          </Routes>
        </div>
      </div>
    <Footer />
    </div>
  )
}



export default App
