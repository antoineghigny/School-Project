<template>
    <div class="input-group">
        <input
            id="btn-input"
            type="text"
            name="content"
            class="form-control input-sm"
            placeholder="Type your message here..."
            v-model="newMessage"
            @keyup.enter="sendMessage"
        />
        <span class="input-group-btn">
      <button class="btn btn-primary btn-sm" id="btn-chat" @click="sendMessage">
        Send
      </button>
    </span>
    </div>
</template>
<script>
export default {
    //Takes the "user" props from <chat-form> … :user="{{ Auth::user() }}"></chat-form> in the parent chat.blade.php.
    props: ["user", "friend"],

    data() {
        return {
            newMessage: null,
            users: [],
            allMessages: [],
        };

    },

    // Emitting an event called "friendsent" with the friend object.
    created() {
        this.$emit("friendsent", {
            friend: this.friend,
        });
        console.log('hey pushmessage')

        // moi auth
        window.Echo.private('encrypted-privatechat.' + this.user.id).listen(
            "PrivateMessageSent",
            (e) => {
                // ami (celui qui a envoyé le message) == l'ami que je parle
                if (e.sender_id.id === this.friend.id) {
                    this.$emit("pushmessage", {
                        user: e.sender_id,
                        friend: e.receiver_id,
                        message: JSON.parse(e.message).message,
                    });
                }
            }
        )
    },

    methods: {
        sendMessage() {
            if (this.newMessage == null) {
                return alert('Please enter message');
            }
            //Emit a "messagesent" event including the user who sent the message along with the message content
            this.$emit("messagesent", {
                user: this.user,
                friend: this.friend,
                message: this.newMessage,
            });
            //Clear the input
            this.newMessage = null;
        },
    },
};
</script>
