/**
 * First we will load all of this project's JavaScript dependencies which
 * includes Vue and other libraries. It is a great starting point when
 * building robust, powerful web applications using Vue and Laravel.
 */

require('./bootstrap');

window.Vue = require('vue').default;

/**
 * The following block of code may be used to automatically register your
 * Vue components. It will recursively scan this directory for the Vue
 * components and automatically register them with their "basename".
 *
 * Eg. ./components/ExampleComponent.vue -> <example-component></example-component>
 */

// const files = require.context('./', true, /\.vue$/i)
// files.keys().map(key => Vue.component(key.split('/').pop().split('.')[0], files(key).default))

Vue.component('chat-messages', require('./components/ChatMessage.vue').default);
Vue.component('chat-form', require('./components/ChatForm.vue').default);
Vue.component('friends', require('./components/FriendsComponent.vue').default);
Vue.component('friend-request', require('./components/FriendsRequestComponent.vue').default);
Vue.component('remove-friends', require('./components/RemoveFriendsComponent.vue').default);

/**
 * Next, we will create a fresh Vue application instance and attach it to
 * the page. Then, you may begin adding components to this application
 * or customize the JavaScript scaffolding to fit your unique needs.
 */


const app = new Vue({
    el: '#app',
    //Store chat messages for display in this array.
    data: {
        messages: [],
        error: null
    },


    methods: {
        /**
         * A method that is called when a user clicks on a friend in the friends list. It takes the friend object as a
         * parameter and saves it in the friend variable. It then makes a GET request to the messages route in our Laravel
         * server to fetch all the messages. It then saves the response in the messages array to display on the chat view.
         * @param friend a friend in the friends list
         */



        fetchMessages({friend}) {
            this.friend = friend;
            //GET request to the messages route in our Laravel server to fetch all the messages
            axios.get('/api/messages/' + this.friend.id, {'headers': {'actualDate': Date.now()}}).then(response => {
                //Save the response in the messages array to display on the chat view
                this.messages = response.data;
            });
        },

        /* Pushing the message to the messages array and then posting it to the messages route. */
        addMessage(message) {
            this.messages.push(message);
            //POST request to the messages route with the message data in order for our Laravel server to broadcast it.
            return axios.post('/api/messages/' + this.friend.id, message).then(response => {
                console.log(response.data);
            }).catch(err => {
                console.log(err.response.data)
            });
        },

        /* Adding a friend to the database. */
        addFriend(friends) {
            console.log(friends.friends)
            axios.post('/api/addFriend/' + friends.friends).then(response => {
                console.log(response.data);
            });
        },

        /* Accepting a friend request. */
        acceptFriend(friends) {
            console.log(friends.friends)
            axios.post('/api/acceptFriend/' + friends.friends).then(response => {
                console.log(response.data);
            });
        },

        /**
         * The function takes in an object with a friends property, and then uses axios to send a post request to the
         * server with the friends property as the parameter
         * @param friends - This is the friends object that is being passed in from the component.
         */
        removeFriend(friends) {
            console.log(friends.friends)
            axios.post('/api/friendsToRemove/' + friends.friends).then(response => {
                console.log(response.data);
            });
        },

        pushMessage(message) {
            this.messages.push(message);
        }
    }
});
