<template>
    <div class="container">
        <div class="col">
            <div class="container">
                <h2>List users</h2>
                <div class="select-box">
                    <div class="options-container" id="container">
                        <div class="option " v-for="friend in friends" :key="friend.id">
                            <input type="radio" class="radio" :id=friend.id name="category"/>
                            <label id="friendid">{{ friend.name }}</label>
                        </div>
                    </div>
                    <div class="selected" id="friendToAdd">Select the user you want to add as a friend</div>
                    <div class="search-box">
                        <input type="text" placeholder="Start Typing..."/>
                    </div>
                </div>
                <button class="btn btn-success btn-lg btn-block" id="btn-chat" @click="acceptFriend">
                    Add as friend
                </button>
                <button class="btn btn-danger btn-lg btn-block" @click="acceptFriend">
                    Refuse
                </button>
                <p class="text-danger"></p>
            </div>
        </div>
    </div>
</template>

<script>

export default {
    props: ["friends"],
    data() {
        return {
            newMessage: null,
            friend: null,
        };
    },

    methods: {
        // A function that is called when the user clicks on the button "Add as friend". It checks if the user has selected
        // a friend to add. If not, it displays an error message. If yes, it emits an event "friendaccept" with the id of
        // the friend to add.
        acceptFriend() {
            document.querySelector('.text-danger').reveal;
            if(document.querySelector("#friendToAdd").innerHTML !=  "Add as friend"){
                this.newMessage = document.querySelectorAll('input[type="radio"]:checked')[0].id;
                //Emit a "messagesent" event including the user who sent the message along with the message content
                this.$emit("friendaccept", {
                    friends: this.newMessage,
                });
                document.querySelector('.text-danger').style.visibility = 'hidden';
            }else{
                document.querySelector('.text-danger').style.visibility = 'visible';
                const el = document.querySelector(".text-danger");
                el.innerHTML = "Please select a user";
            }
        },

        // A function that is called when the user clicks on the button "Refuse". It checks if the user has selected
        //  a friend to add. If not, it displays an error message. If yes, it emits an event "refuserequest" with
        // the id of the friend to add.
        refuseFriend(){
            document.querySelector('.text-danger').reveal;
            if(document.querySelector("#friendToAdd").innerHTML !=  "Add as friend"){
                this.newMessage = document.querySelectorAll('input[type="radio"]:checked')[0].id;
                //Emit a "messagesent" event including the user who sent the message along with the message content
                this.$emit("refuserequest", {
                    friends: this.newMessage,
                });
                document.querySelector('.text-danger').style.visibility = 'hidden';
            }else{
                document.querySelector('.text-danger').style.visibility = 'visible';
                const el = document.querySelector(".text-danger");
                el.innerHTML = "Please select a user";
            }
        }
    },
}

</script>

<style scoped>

</style>
