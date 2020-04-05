using System.Collections;
using System.Collections.Generic;
using System.IO.Ports;
using UnityEngine;

public class RightLeftCube : MonoBehaviour
{
	public float speed;									// determines the speed of the cube
	private float amountToMove;							// calculated by the speed
	SerialPort sp = new SerialPort("COM3", 9600);		// opens up communication for the Arduino

    // Start is called before the first frame update
    void Start()
    {
		sp.Open();
		sp.ReadTimeout = 1;

		//CubeController();
    }

    // Update is called once per frame
    void Update()
    {
		amountToMove = speed * Time.deltaTime;
		//transform.Translate(Vector3.left * amountToMove, Space.World);
		if (sp.IsOpen) 
		{
			try 
			{
				CubeController(sp.ReadByte());
			} catch (System.Exception)
			{
				
			}
		}
    }

	// handles the movement of the cube
	void CubeController(int direction)
	{
		if (direction == 0) 
		{
			Debug.Log(direction);
			transform.Translate(Vector3.left * amountToMove, Space.World);
		}
		if (direction == 1) 
		{
			Debug.Log(direction);
			transform.Translate(Vector3.right * amountToMove, Space.World);
		}
		if (direction == 2) 
		{
			Debug.Log(direction);
			transform.Translate(Vector3.up * amountToMove, Space.World);
		}
		if (direction == 3) 
		{
			Debug.Log(direction);
			transform.Translate(Vector3.down * amountToMove, Space.World);
		}


	}
}
