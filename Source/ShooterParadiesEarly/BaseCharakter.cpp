// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharakter.h"
#include "ActorHelper.h"

// Sets default values
ABaseCharakter::ABaseCharakter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	InitializeComponents()




	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("PlayerCollision"));
	collision->SetupAttachment(RootComponent);
	collision->SetCapsuleSize(100,100);

	movecomp = GetCharacterMovement();

	bUseControllerRotationYaw = false;
	cam = CreateDefaultSubobject<UCameraComponent>(TEXT("BaseCamera"));

	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpingArmComp"));
	arm->SetupAttachment(RootComponent);
	arm->TargetArmLength = 300.f;
	arm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	arm->bEnableCameraLag = true;
	arm->CameraLagSpeed = 2;
	arm->CameraLagMaxDistance = 1.5f;

	arm->bEnableCameraRotationLag = true;
	arm->CameraRotationLagSpeed = 4;
	arm->CameraLagMaxTimeStep = 1;
	
	cam->AttachToComponent(arm, rules, USpringArmComponent::SocketName);

	speed = 0.5f;
	walking = true;

	currentStamina = initStamina;

}

auto ABaseCharakter::InitializeComponents(void) -> void
{
	if (!RootComponent) RootComponent = CreateDefaultSubobject<USceneComponent>(FN_ROOT);
	if (!m_pMesh) m_pMesh = InitSkeletalMesh(S_Mesh_PATH, FN_MESH, DEFAULT_MESH_SCALE);
	if (!m_pArm) m_pArm = InitCameraArm();
	if (!m_pCamera) m_pCamera = InitCamera();
	if (!m_pMovement) m_pMovement = InitMovement();
}

auto ABaseCharakter::InitSkeletalMesh(const FString& a_sMeshPath, const FName& a_sName, const FVector& a_scale) -> USkeletalMeshComponent*
{
	auto mesh = CreateDefaultSubobject<USkeletalMesh>(a_sName);

	mesh->SetupAttachment(RootComponent);
	mesh->SetSkeletalMesh(ActorHelper::FindObject<USkeletalMesh>(a_sMeshPath));
	mesh->SetRelativeRotation(DEFAULT_MESH_ROT);
	mesh->SetRelativeScale3D(a_scale);
	mesh->OverrideAnimationData(m_pIdelAnim, true);

	return mesh;
}

auto ABaseCharakter::InitCameraArm(void) -> USpringArmComponent*
{
	auto arm = CreateDefaultSubobject<USpringArmComponent>(m_pArm);

	arm->SetupAttachment(RootComponent);
	arm->TargetArmLength = DEFAULT_ARM_LENGHT;
	arm->arm->SetRelativeRotation(DEFAULT_ARM_ROT);
	arm->bEnableCameraLag = CameraLag;
	if (CameraLag == true)
	{
		arm->CameraLagSpeed = CameraLagSpeed;
		arm->CameraLagMaxDistance = CameraLagMaxDistance;
	}
	arm->bEnableCameraRotationLag = CameraRotationLag;
	if (CameraRotationLag == true)
	{
		arm->CameraRotationLagSpeed = CameraRotationLagSpeed;
		arm->CameraLagMaxTimeStep = CameraLagMaxTime;
	}

	return arm;
}

auto ABaseCharakter::InitCamera(void) -> UCameraComponent*
{
	auto camera = CreateDefaultSubobject<UCameraComponent>(m_pCamera);

	camera->SetRelativeLocation(DEFAULT_CAM_LOC);
	camera->SetRelativeRotation(DEFAULT_CAM_ROT);
	camera->SetupAttachment(RootComponent);
	camera->AttachToComponent(arm, rules, USpringArmComponent::SocketName);

	return camera;
}

auto ABaseCharakter::InitMovement(void) -> UFloatingPawnMovement*
{
	auto movement = CreateDefaultSubobject<UFloatingPawnMovement>(FN_MOVE);
	movement->UpdatedComponent = RootComponent;

	return nullptr;
}

auto ABaseCharakter::InitKeyMapping(void) -> void
{
	//AXIS Input

	auto forwardAxisKey		= FInputAxisKeyMapping(FORWARD_AXIS,	EKeys::W,				POS_INPUT_SCALE);
	auto backwardAxisKey	= FInputAxisKeyMapping(FORWARD_AXIS,	EKeys::S,				NEG_INPUT_SCALE);
	auto rightAxisKey		= FInputAxisKeyMapping(RIGHT_AXIS,		EKeys::D,				POS_INPUT_SCALE);
	auto leftAxisKey		= FInputAxisKeyMapping(RIGHT_AXIS,		EKeys::A,				NEG_INPUT_SCALE);

	auto mouseAxis			= FInputAxisKeyMapping(M_WHEEL_AXIS,	EKeys::MouseScrollUp,	M_W_POS_INPUT_SCALE);
	auto negmouseAxis		= FInputAxisKeyMapping(M_WHEEL_AXIS,	EKeys::MouseScrollDown, M_W_NEG_INPUT_SCALE);

	//Action Input

	auto primaryMouseBTN	= FInputActionKeyMapping(MousePrimaryBTN,	EKeys::LeftMouseButton);
	auto secondaryMouseBTN	= FInputActionKeyMapping(MouseSecondaryBTN, EKeys::RightMouseButton);
	auto middleMouseBTN		= FInputActionKeyMapping(MouseMiddleBTN,	EKeys::MiddleMouseButton);
	auto jumpBTN			= FInputActionKeyMapping(JumpBTN,			EKeys::SpaceBar);
	auto cameraBTN			= FInputActionKeyMapping(CameraToggle,		EKeys::LeftAlt);

	//Axis Mapping

	UPlayerInput::AddEngineDefinedAxisMapping(forwardAxisKey);
	UPlayerInput::AddEngineDefinedAxisMapping(backwardAxisKey);
	UPlayerInput::AddEngineDefinedAxisMapping(rightAxisKey);
	UPlayerInput::AddEngineDefinedAxisMapping(leftAxisKey);

	UPlayerInput::AddEngineDefinedAxisMapping(mouseAxis);
	UPlayerInput::AddEngineDefinedAxisMapping(negmouseAxis);

	//Actin Mapping

	UPlayerInput::AddEngineDefinedActionMapping(primaryMouseBTN);
	UPlayerInput::AddEngineDefinedActionMapping(secondaryMouseBTN);
	UPlayerInput::AddEngineDefinedActionMapping(middleMouseBTN);
	UPlayerInput::AddEngineDefinedActionMapping(jumpBTN);
	UPlayerInput::AddEngineDefinedActionMapping(cameraBTN);
}

auto ABaseCharakter::EnableInput(UInputComponent* _playerInputComponent) -> void
{
	InitKeyMapping();
	_playerInputComponent->BindAxis(FORWARD_AXIS, this, &ABaseCharakter::OnMovingForward);
	_playerInputComponent->BindAxis(RIGHT_AXIS, this, &ABaseCharakter::OnMovingRight);
	_playerInputComponent->BindAxis(M_WHEEL_AXIS, this, &ABaseCharakter::MouseWeehl);

	_playerInputComponent->BindAction(MousePrimaryBTN, EKeys::LeftMouseButton, &ABaseCharakter::OnPrimaryAction);

}

// Called when the game starts or when spawned
void ABaseCharakter::BeginPlay()
{
	Super::BeginPlay();
	arm->AttachToComponent(GetMesh() ,rules, "headSocket");
	collision->AttachToComponent(GetMesh(), rules);
	collision->GetBodySetup();
}

// Called every frame
void ABaseCharakter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCurrentStamina(-DeltaTime * 0.01f * (initStamina));

	if (jumping)
	{
		Jump();
	}
	if (!player_has_weapon && OnUseItem.IsBound())
	{
		player_has_weapon = true;
	}

}

// Called to bind functionality to input
void ABaseCharakter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Keyboard Input Setup
	InputComponent->BindAxis("Horizontal", this, &ABaseCharakter::MoveHorizontal);
	InputComponent->BindAxis("Vertical", this, &ABaseCharakter::MoveVertical);
	InputComponent->BindAction("horizontal", IE_Released, this, &ABaseCharakter::StopMoveHorizontal);
	InputComponent->BindAction("vertical", IE_Released, this, &ABaseCharakter::StopMoveVertical);
	 
	InputComponent->BindAction("Jump", IE_Pressed, this, &ABaseCharakter::CheckJump);
	InputComponent->BindAction("Jump", IE_Released, this, &ABaseCharakter::CheckJump);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &ABaseCharakter::Sprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &ABaseCharakter::Sprint);

	InputComponent->BindAction("ChangeCamera", IE_Pressed, this, &ABaseCharakter::SwitchCamera);

	// Mouse Input Setup
	InputComponent->BindAxis("HorizontalRot", this, &ABaseCharakter::RotHorizontal);
	InputComponent->BindAxis("VerticalRot", this, &ABaseCharakter::RotVertical);
	InputComponent->BindAxis("MouseWheel", this, &ABaseCharakter::MouseWeehl);

	InputComponent->BindAction("PrimaryAction", IE_Pressed, this, &ABaseCharakter::OnPrimaryAction);
	InputComponent->BindAction("ToogleMouseWheel",IE_Pressed, this, &ABaseCharakter::MouseWeehlToggle);


}

//	KEYBOARD CONTROLLS

void ABaseCharakter::MoveHorizontal(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value * speed);
		horizontalSpeed = 1;
	}
	
}

void ABaseCharakter::StopMoveHorizontal()
{
	horizontalSpeed = 0;
}

void ABaseCharakter::MoveVertical(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(), value * speed);
		verticalSpeed = 1;
	}
	
}

void ABaseCharakter::StopMoveVertical()
{
	verticalSpeed = 0;
}

void ABaseCharakter::CheckJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}

void ABaseCharakter::SwitchCamera()
{
	if (firstPerson)
	{
		arm->TargetArmLength = 300.f;
		arm->SetRelativeRotation(FRotator(-45, 0, 0));
		cam->SetRelativeRotation(FRotator(0, 0, 0));
		cam->AttachToComponent(arm, rules, USpringArmComponent::SocketName);
		firstPerson = false;
	}
	else
	{
		cam->AttachToComponent(GetMesh(), rules, "headSocket");
		firstPerson = true;
	}
}

void ABaseCharakter::Sprint()
{
	walking = !walking;

	if (walking)
	{
		speed = 1.0f;
	}
	else
	{
		speed = 1.3f;
	}
}

//	MOUSE CONTROLLS

void ABaseCharakter::RotHorizontal(float value)
{
	if(value)
	{
		AddActorLocalRotation(FRotator(0,value,0));
	}
}

void ABaseCharakter::RotVertical(float value)
{
	if (value)
	{
		float temp = 0;
		if (firstPerson)
		{
			temp = cam->GetRelativeRotation().Pitch + value;
			if (temp < 65 && temp > -65)
			{
				cam->AddLocalRotation(FRotator(value, 0, 0));
			}
		}
		else
		{
			temp = cam->GetRelativeRotation().Pitch + value;
			if (temp < 25 && temp > -65)
			{
				arm->AddLocalRotation(FRotator(value, 0, 0));
			}
		}

	}
}

void ABaseCharakter::MouseWeehl(float value)
{
	if (value)
	{
		float temp = 0;
		if (zoomOrWpn)
		{
			temp = arm->TargetArmLength + (value * -10);
			if (temp < 310 && temp > 140)
			{
				arm->TargetArmLength = temp;
			}
		}
		else
		{
			//WPN SWITCH
		}
	}
}

void ABaseCharakter::MouseWeehlToggle()
{
	zoomOrWpn = !zoomOrWpn;
}

void ABaseCharakter::OnPrimaryAction()
{
	OnUseItem.Broadcast();
}

float ABaseCharakter::GetCurrentStamina()
{
	return currentStamina;
}

float ABaseCharakter::GetInitialStamina()
{
	return initStamina;
}

void ABaseCharakter::UpdateCurrentStamina(float Stamina)
{
	currentStamina = currentStamina + Stamina;
}

