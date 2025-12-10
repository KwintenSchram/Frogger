/*
 * GameEnums.h
 * Enumerations for game states, modes, and difficulty levels
 */

#ifndef GAMEENUMS_H_
#define GAMEENUMS_H_

namespace frogger
{
	// Game state machine states
	enum class GameState
	{
		StartMenu,      // B: start menu
		Highscore,      // H: highscore display menu
		Settings,       // S: settings menu
		Victory,        // V: victory screen
		GameOver,       // G: game over screen
		Help,           // A: help screen
		EndlessMode,    // E: Endless game mode
		ClassicMode,    // C: classic game mode
		Quit            // Q: quit state
	};

	// Game mode
	enum class GameMode
	{
		Endless,  // E: Endless game mode
		Classic   // C: Classic game mode
	};

	// Difficulty level
	enum class Difficulty
	{
		Easy,     // E: Easy difficulty
		Medium,   // M: Medium difficulty
		Hard      // H: Hard difficulty
	};

	// Row types
	enum class RowType
	{
		Start,       // A: First row (player starts here)
		Obstacle,    // B: Obstacle row (obstacles visible, lanes invisible)
		Lane,        // C: Lane row (obstacles invisible, lanes visible)
		Middle,      // D: Middle row (no movement, can contain bushes)
		End          // E: Last row (goal row)
	};

	// Helper function to convert GameState to character (for backward compatibility)
	inline char gameStateToChar(GameState state)
	{
		switch (state)
		{
			case GameState::StartMenu:    return 'B';
			case GameState::Highscore:    return 'H';
			case GameState::Settings:     return 'S';
			case GameState::Victory:      return 'V';
			case GameState::GameOver:     return 'G';
			case GameState::Help:         return 'A';
			case GameState::EndlessMode:  return 'E';
			case GameState::ClassicMode:  return 'C';
			case GameState::Quit:         return 'Q';
			default:                      return 'B';
		}
	}

	// Helper function to convert character to GameState (for backward compatibility)
	inline GameState charToGameState(char c)
	{
		switch (c)
		{
			case 'B': return GameState::StartMenu;
			case 'H': return GameState::Highscore;
			case 'S': return GameState::Settings;
			case 'V': return GameState::Victory;
			case 'G': return GameState::GameOver;
			case 'A': return GameState::Help;
			case 'E': return GameState::EndlessMode;
			case 'C': return GameState::ClassicMode;
			case 'Q': return GameState::Quit;
			default:  return GameState::StartMenu;
		}
	}

	// Helper function to convert GameMode to character
	inline char gameModeToChar(GameMode mode)
	{
		return (mode == GameMode::Endless) ? 'E' : 'C';
	}

	// Helper function to convert character to GameMode
	inline GameMode charToGameMode(char c)
	{
		return (c == 'E') ? GameMode::Endless : GameMode::Classic;
	}

	// Helper function to convert Difficulty to character
	inline char difficultyToChar(Difficulty diff)
	{
		switch (diff)
		{
			case Difficulty::Easy:   return 'E';
			case Difficulty::Medium: return 'M';
			case Difficulty::Hard:   return 'H';
			default:                 return 'E';
		}
	}

	// Helper function to convert character to Difficulty
	inline Difficulty charToDifficulty(char c)
	{
		switch (c)
		{
			case 'E': return Difficulty::Easy;
			case 'M': return Difficulty::Medium;
			case 'H': return Difficulty::Hard;
			default:  return Difficulty::Easy;
		}
	}

	// Helper to check if state is a menu state
	inline bool isMenuState(GameState state)
	{
		return state == GameState::StartMenu ||
		       state == GameState::Highscore ||
		       state == GameState::Settings ||
		       state == GameState::Victory ||
		       state == GameState::GameOver ||
		       state == GameState::Help;
	}

	// Helper to check if state is a gameplay state
	inline bool isGameplayState(GameState state)
	{
		return state == GameState::EndlessMode ||
		       state == GameState::ClassicMode;
	}
}

#endif /* GAMEENUMS_H_ */
