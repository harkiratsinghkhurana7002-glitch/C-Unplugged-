# USER GUIDE
### Please Read the Guide Before Use

## Main Features

### 1. Song Library Management (Read-Only)

- Loads songs from a binary file: `Lib.dat`
- Displays all songs in a formatted text file: `Lib.txt`
- Each song has a unique song ID generated internally and is **not shown to the user**.

### 2. Album Creation and Management

- Create new albums using a name.
- Add songs to albums using the song index from the Library.
- Delete songs from albums using the song index inside the album.
- Delete entire albums.
- All albums, along with their songs, are saved to `alb.dat` for persistent storage across sessions.

### 3. Playlist / Queue Creation and Playback

- Add individual songs to the playlist.
- Add entire albums to the playlist.
- Delete songs from the playlist.
- Playlist supports:
  - **Next Song**
  - **Previous Song**
  - **Current Song**
  - **Looping Playback**

### 4. Command Logging (Across Sessions)

- Every user action is logged permanently.
- The log is maintained across multiple program sessions.

### 5. CLI Menu

- A full, numbered menu allows users to perform all operations using simple inputs.

---

## ⚠️ IMPORTANT CAUTION — Library Creation Function

### `createLib.c` is ONE-TIME USE ONLY

The Library Creator function was written to generate `Lib.dat` and `Lib.txt` initially. It is required **only for the initial creation of the library**.

> **❗ Users MUST NOT run `createLib.c` again after the library has been created.**

Running it again may:

- Overwrite `Lib.dat`
- Break song IDs
- Corrupt the library linked list
- Corrupt albums and playlists
- Make the entire program inconsistent

### Modifying the Library

The library is **not designed to be edited through the application**.

If the library needs to be modified later, the following files must be manually updated:

1. `Lib.txt` — Human-readable song listing
2. `Lib.dat` — Binary file from which the program loads songs

**Do not use the application to modify the Library.**

---

# How to Run the Program

Open a terminal inside the project's root folder and compile the program using:

```bash
gcc Source/main.c Source/lib_fxn.c Source/alb_fxn.c Source/playlist_fxn.c -o cUnplugged
