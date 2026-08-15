# Ball-Beam-project
<table>
  <tr>
    <td>
      <img src="https://github.com/user-attachments/assets/ef0edc0c-157b-4e53-8a3d-4d727a81813b" width="400"/><br/>
      <img src="https://github.com/user-attachments/assets/28f9616a-aa16-4fc2-9c73-5c23a127b2fb" width="400"/>
    </td>
    <td><img src="https://github.com/user-attachments/assets/567643d7-1f37-4fec-8cc7-5dc4f981d1b3" width="400"/></td>
    <td><img src="https://github.com/user-attachments/assets/fb3fd9a8-8f6a-4d7f-953b-bac5e488c99a" width="400"/></td>
  </tr>
</table>
This is repository for the Ball &amp; Beam project showcasing the projects control system, code, and CAD pictures.

# Overview
The project's main aim is to balance a table-tennis ball at a specified setpoint. The ball position is controlled using a PID controller with the angle of the servo as the input to the system and feedback data is through a Time of Flight (ToF) sensor. A custom robotic joint linkage is attached to one side of the beam by a pivot, and the servo motor is what actuates the arm to move one side of the beam vertically to roll the ball to desired position. the system is simulated using MATLAB to further analyse the properties and behavior of the closed loop response.

# Running the model
In order to run model simply run the MATLAB script and the model will automatically run the simulation and the script will generate the relevant plots and data.
