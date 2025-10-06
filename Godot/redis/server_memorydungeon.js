const express = require("express");
const bcrypt = require("bcrypt");

const BASE = "/memorydungeon";

const REDIS_MD_NS = "md";

function apiMemoryDungeon({ redis, authKey }) {
    if (!redis) throw new Error("Redis required");

    const router = express.Router();
    router.use(express.json());

    const saveKey = (u) => `${REDIS_MD_NS}:user:data:${u}`;

    // For Godot
    router.use('/', express.static(__dirname + "/MemoryDungeon"));
    router.get('/',function (req, res) {
        res.sendFile(__dirname + '/MemoryDungeon/MemoryDungeon.html');
    });

    // POST /save
    router.post("/save", async (req, res) => {
        const { username, password, save } = req.body || {};
        if (!username || !password || typeof save !== "object") {
            return res.status(400).json({ error: "bad_request" });
        }

        const user = await redis.hGetAll(authKey(username));
        if (!user.password_hash || !(await bcrypt.compare(password, user.password_hash))) {
            return res.status(401).json({ error: "unauthorized" });
        }

        // Whitelist fields you accept
        const allowed = ["version", "best_level", "saved_level", "gold", "ai_forget_rate", "hero", "owned_k", "owned_sp"];
        const toStore = {};
        for (const k of allowed) if (k in save) toStore[k] = String(save[k]);

        await redis.hSet(saveKey(username), toStore);
        res.json({ status: "saved" });
    });

    // GET /load
    router.get("/load", async (req, res) => {
        const { username, password } = req.query || {};
        if (!username || !password) return res.status(400).json({ error: "bad_request" });

        const user = await redis.hGetAll(authKey(username));
        if (!user.password_hash || !(await bcrypt.compare(password, user.password_hash))) {
            return res.status(401).json({ error: "unauthorized" });
        }

        const save = await redis.hGetAll(saveKey(username));
        res.json({ save: Object.keys(save).length ? save : null });
    });

    return { base: BASE, router };
}

module.exports = { apiMemoryDungeon };