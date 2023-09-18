import React, { useEffect, useState } from 'react';
import axios from 'axios';

export default function Index() {

  const [data, setData] = useState(0);

  const hostEsp = import.meta.env.VITE_HOST_ESP

  console.log(hostEsp);

  useEffect(() => {
    fetchData()

    const interval = setInterval(() => {
      fetchData();
    }, 1000);

    return () => {
      clearInterval(interval);
    };
  }, []);


  const fetchData = async () => {
    try {
      const response = await axios.get(`${hostEsp}/sensor`);
      setData(response.data);
      console.log(response.data)
    } catch (error) {
      console.error(error);
    }
  };


  const buttonClick = async () => {
    await axios.post(`${hostEsp}/sensor`, null, {
      params: {
        "GPIO2": "toggle"
      }
    });
    fetchData();
  };


  const handleSubmit = async (event) => {
    event.preventDefault();
  };

  return (<>
    <h4>Temperatura CPU: {data ? data.SENSOR.TemperatureCPU : "..."}°C</h4>
    <h4>ESTADO LED: {data ? data.SENSOR.GPIO2 : "..."}</h4>

    <form onSubmit={handleSubmit}>
      Control LED: <button onClick={buttonClick}>Toogle</button>
    </form>

  </>)
}