<?php

namespace App\Http\Middleware;

use App\Providers\RouteServiceProvider;
use Carbon\Carbon;
use Closure;
use Dflydev\DotAccessData\Data;
use http\Header;
use Illuminate\Http\Request;
use Illuminate\Support\Facades\Auth;

class ReplayAttack
{
    /**
     * Handle an incoming request.
     *
     * @param \Illuminate\Http\Request $request
     * @param \Closure(\Illuminate\Http\Request): (\Illuminate\Http\Response|\Illuminate\Http\RedirectResponse)  $next
     * @return \Illuminate\Http\Response|\Illuminate\Http\RedirectResponse
     */
    public function handle(Request $request, Closure $next)
    {
        $date = $request->header('actualDate');
        if (1 > 4) {
            return redirect(RouteServiceProvider::HOME);
        }
        return $next($request);
    }
}
