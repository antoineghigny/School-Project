<?php

namespace App\Http\Requests;

use Illuminate\Foundation\Http\FormRequest;

class CheckMessage extends FormRequest
{
    /**
     * Determine if the user is authorized to make this request.
     *
     * @return bool
     */
    public function authorize()
    {
        return true;
    }

    /**
     * Get the validation rules that apply to the request.
     *
     * @return array<string, mixed>
     */
    public function rules()
    {
        return [
            'message' => 'bail|required|between:3,200',
        ];
    }

    public function messages() {
        return [
            'content.required' => "Il faut renseigner un message pour l'envoyer !",
            'content.between' => "Votre message doit faire entre 5 et 200 caractères.",
        ];
    }
}
