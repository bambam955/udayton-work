using UnityEngine;
using UnityEngine.SceneManagement;

public class Bird : MonoBehaviour
{
    Vector3 _initialPosition;
    bool _wasLaunched = false;
    float _timeSittingAround = 0;
    [SerializeField] float _launchPower = 250;

    void Awake()
    {
        _initialPosition = transform.position;
    }

    void Update()
    {
        GetComponent<LineRenderer>().SetPosition(0, transform.position);
        GetComponent<LineRenderer>().SetPosition(1, _initialPosition);

        if (_wasLaunched && 
            GetComponent<Rigidbody2D>().linearVelocity.magnitude <= 0.1)
        {
            _timeSittingAround += Time.deltaTime;
        }

        if (transform.position.y > 10 ||
            transform.position.y < -10 ||
            transform.position.x > 20 ||
            transform.position.x < -20 ||
            _timeSittingAround > 3) 
        {
            string currSceneName = SceneManager.GetActiveScene().name;
            SceneManager.LoadScene(currSceneName);
        }
    }

    void OnMouseDown()
    {
        GetComponent<LineRenderer>().enabled = true;
    }

    void OnMouseUp()
    {
        Vector2 direction = _initialPosition - transform.position;

        GetComponent<Rigidbody2D>().AddForce(direction * _launchPower);
        GetComponent<Rigidbody2D>().gravityScale = 1;
        _wasLaunched = true;

        GetComponent<LineRenderer>().enabled = false;
    }

    void OnMouseDrag()
    {
        Vector3 newPosition = Camera.main.ScreenToWorldPoint(Input.mousePosition);
        transform.position = new Vector3(newPosition.x, newPosition.y);
    }
}
