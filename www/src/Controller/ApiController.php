<?php
// src/Controller/ApiController.php
namespace App\Controller;


use App\Entity\AirQuality;
use DateTime;
use FOS\RestBundle\Controller\Annotations as Rest;
use Symfony\Bundle\FrameworkBundle\Controller\Controller;
use Symfony\Component\HttpFoundation\Request;
use Symfony\Component\Routing\Annotation\Route;

/**
 *
 * @Route("/api")
 */
class ApiController extends Controller
{

    /**
     *
     * @Rest\Post("/data")
     * @Rest\View()
     * @param Request $request
     * @return array
     */

    public function dataAction(Request $request)
    {

        $quality = $request->request->get('air');
        $date = $request->request->get('date');

        $entityManager = $this->getDoctrine()->getManager();


        $dateTime = new DateTime();
        $dateTime->setTimestamp($date);

        $airQuality = new AirQuality();
        $airQuality->setQuality($quality);
        $airQuality->setDate($dateTime);

        $entityManager->persist($airQuality);

        // actually executes the queries (i.e. the INSERT query)
        $entityManager->flush();

        $data = [
            "id" => $airQuality->getId(),
            "quality" => $airQuality->getQuality(),
            "date" => $airQuality->getDate(),
        ];

        return $data;
    }


    /**
     * @Rest\Get("/air", name="get_data")
     * @Rest\View()
     */
    public function getData() {

        $rep = $this->getDoctrine()->getRepository(AirQuality::class);

        return $rep->findOnlyQuality();

    }

}