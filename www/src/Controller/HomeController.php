<?php
/**
 * Created by PhpStorm.
 * User: mbutt
 * Date: 27/03/2018
 * Time: 11:42
 */

namespace App\Controller;



use App\Entity\AirQuality;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\Routing\Annotation\Route;

class HomeController extends Controller
{


    /**
     * @Route("/", name="home")
     */
    public function homeAction(){


        $data = $this->getDoctrine()->getRepository(AirQuality::class)
            ->findAll();

        return $this->render('home.html.twig');
    }
}