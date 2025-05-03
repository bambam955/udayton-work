using UnityEngine;

public class Enemy : MonoBehaviour
{
    [SerializeField] private GameObject _cloudParticlePrefab;

    void OnCollisionEnter2D(Collision2D collision)
    {
        Enemy enemy = collision.collider.GetComponent<Enemy>();
        if (enemy != null)
        {
            return;
        }

        Bird bird = collision.collider.GetComponent<Bird>();
        if (bird != null)
        {
            killEnemy();
            return;
        }

        if (collision.contacts[0].normal.y < 0)
        {
            killEnemy();
        }
    }

    void killEnemy() 
    {
        Instantiate(_cloudParticlePrefab, transform.position, Quaternion.identity);
        Destroy(gameObject);
    }
}
