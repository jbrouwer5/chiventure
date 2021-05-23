{
    "GAME": {
        "start": "room_A",
        "intro": "This is the intro",
        "end": {
            "in_room": "room_C"
        }
    },
    "ROOMS": {
        "room_A": {
            "short_desc": "This is room A",
            "long_desc": "This is room A. There's a chair and an exit to the south.",
            "connections": [
                {
                    "to": "room_B",
                    "direction": "SOUTH"
                }
            ]
        },
        "room_B": {
            "short_desc": "This is room B",
            "long_desc": "This is room B. There's a table and an exit to the west.",
            "connections": [
                {
                    "to": "room_C",
                    "direction": "WEST"
                }
            ]
        },
        "room_C": {
            "short_desc": "This is room C",
            "long_desc": "This is room C, the final room in the game",
            "connections": [
                {
                    "to": "room_A",
                    "direction": "NORTH"
                }
            ]
        }
    },
    "ITEMS": {
        "CHAIR": {
            "short_desc": "This is a chair",
            "long_desc": "This is a chair long",
            "in": "room_A",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the chair",
                    "text_fail": "You cannot push this chair"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the chair",
                    "text_fail": "You cannot pull this chair"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the chair",
                    "text_fail": "You cannot take this chair"
                }
            ]
        },
        "TABLE": {
            "short_desc": "This is a table",
            "long_desc": "This is a table long",
            "in": "room_B",
            "actions": [
                {
                    "action": "PUSH",
                    "text_success": "You push the table",
                    "text_fail": "You cannot push this table"
                },
                {
                    "action": "PULL",
                    "text_success": "You pull the table",
                    "text_fail": "You cannot pull this table"
                },
                {
                    "action": "TAKE",
                    "text_success": "You take the table",
                    "text_fail": "You cannot take this table"
                }
            ]
        }
    },
    "NPCS": {
        "TEST_NPC": {
            "short_desc": "This is a npc",
            "long_desc": "This is a npc long",
            "health": 100,
            "in": "room_A",
            "dialogue": {
                "nodes": [
                    {
                        "id": "1",
                        "npc_dialogue": "D1"
                    },
                    {
                        "id": "2",
                        "npc_dialogue": "D2"
                    }
                ],
                "edges": [
                    {
                        "quip": "Q1",
                        "from_id": "1",
                        "to_id": "2"
                    }
                ]
            }
        }
    }
}
