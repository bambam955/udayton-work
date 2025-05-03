using System.Linq;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.UIElements;

public class LevelController : MonoBehaviour
{
    private static int _nextLevelIndex = -1;
    private static int _attemptsCount = 0;
    private static bool _gameOver = false;
    private Enemy[] _enemies;
    void OnEnable()
    {
        if (_nextLevelIndex == -1)
        {
            string curr = SceneManager.GetActiveScene().name;
            string levelNumberString = curr.Substring("Level".Length);
            int levelNumber = int.Parse(levelNumberString);
            _nextLevelIndex = levelNumber;
            Debug.Log("Starting game! Level: " + _nextLevelIndex);
        }

        if (!_gameOver)
        {
            _attemptsCount++;
            Debug.Log("Total attempts: " + _attemptsCount);
            _enemies = FindObjectsByType<Enemy>(FindObjectsSortMode.None);
        }
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.R))
        {
            _nextLevelIndex = 1;
            _gameOver = false;
            _attemptsCount = 0;
            Debug.Log("Restarting game...");
            SceneManager.LoadScene("Level1");
            return;
        }

        if (_gameOver)
            return;

        foreach (Enemy enemy in _enemies)
        {
            if (enemy != null)
                return;
        }

        Debug.Log("You killed all the enemies!");

        _checkForGameEnd();

        if (_nextLevelIndex < 3)
        {
            _nextLevelIndex++;
            string nextLevelName = "Level" + _nextLevelIndex;
            SceneManager.LoadScene(nextLevelName);
        }
    }

    bool _checkForGameEnd() 
    {
        if (_nextLevelIndex >= 3 || _attemptsCount >= 10)
        {
            _gameOver = true;
            if (_attemptsCount < 10)
            {
                Debug.Log("YOU WIN!!!");
                SceneManager.LoadScene("YouWin");
            }
            else
            {
                Debug.Log("YOU LOSE!!!");
                SceneManager.LoadScene("YouLose");
            }
            return true;
        }
        return false;
    }
}
