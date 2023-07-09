import React, { useEffect, useState } from 'react';
import axios from 'axios';

export default function Index() {

    const [data, setData] = useState(0);



    useEffect(() => {
        const fetchData = async () => {
          try {
            const response = await axios.get(`${import.meta.env.VITE_HOST_ESP}/sensor`);
            setData(response.data);
            console.log(response.data)
          } catch (error) {
            console.error(error);
          }
        };
    
        const interval = setInterval(() => {
          fetchData();
        }, 1000);

        return () => {
          clearInterval(interval);
        };
      }, []);



        return (<>
            <h4>Temperatura CPU: { data ? data.SENSOR.TemperatureCPU : "..." }°C</h4>
            <h4>ESTADO LED: { data ? data.SENSOR.GPIO2 : "..." }</h4>

        </>)
    }