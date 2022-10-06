<template>
    <div class="container">
        <div class="col">
            <div class="container">
                <h2>List users</h2>
                <div class="select-box">
                    <div class="options-container" id="container">
                        <div class="option " v-for="friend in friends" :key="friend.id">
                            <input type="radio" class="radio" :id=friend.id name="category"/>
                            <label class="allFriends" id="friendid">{{ friend.name }}</label>
                        </div>
                    </div>
                    <div class="selected" id="friendToAdd">Select the user you want to add as a friend</div>
                    <div class="search-box">
                        <input type="text" placeholder="Start Typing..."/>
                    </div>
                </div>
                <button class="btn btn-success btn-lg btn-block" id="btn-chat" @click="sendMessage">
                    Select the user you want to add as a friend
                </button>
                <p class="text-danger"></p>
            </div>
        </div>
    </div>
</template>

<script>

import {has} from "lodash";

export default {

    props: ["friends, user"],

    data() {
        return {
            newMessage: null,
            friend: null,
        };
    },

    methods: {
        sendMessage() {
            if (document.querySelector("#friendToAdd").innerHTML !== "Select the user you want to add as a friend") {
                this.newMessage = document.querySelectorAll('input[type="radio"]:checked')[0].id;
                //Emit a "messagesent" event including the user who sent the message along with the message content
                this.$emit("friendsent", {
                    friends: this.newMessage,
                });
                document.querySelector('.text-danger').style.visibility = 'hidden';
            } else {
                document.querySelector('.text-danger').style.visibility = 'visible';
                const el = document.querySelector(".text-danger");
                el.innerHTML = "Please select a user";
            }
        },
    },
}

</script>

<style scoped>

</style>
