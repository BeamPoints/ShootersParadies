  // Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseCharakter.generated.h"


class USoundBase;
class UAnimMontage;
class UInputComponent;
class USceneComponent;
class UCameraComponent;
class UCapsuleComponent;
class USkeletalMeshComponent;
class UCharacterMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseItem);

UCLASS(config = Game)
class SHOOTERPARADIESEARLY_API ABaseCharakter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	const FAttachmentTransformRules rules = rules.SnapToTargetNotIncludingScale;
	ABaseCharakter();

private:
	/*************************************************************************/
	#pragma region INIT
	/*************************************************************************/

	auto InitSkeletalMesh(const FString& a_sMeshPath, const FName& a_sName, const FVector& a_scale) -> USkeletalMeshComponent*;

	auto InitCameraArm(void) -> USpringArmComponent*;
	auto InitCamera(void) -> UCameraComponent*;
	auto InitMovement(void) -> UFloatingPawnMovement*;
	auto InitializeComponents(void) -> void;
	auto InitKeyMapping(void) -> void;
	auto EnableInput(class UInputComponent* _playerInputComponent) -> void;

	#pragma endregion
	/*************************************************************************/
	#pragma region Callbacks
	/*************************************************************************/
	auto OnMovingForward(const float _input) -> void;
	auto OnMovingRight(const float _input) -> void;

	#pragma endregion
	/*************************************************************************/

	// Accessor function for initial stamin 
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetInitialStamina();

	// Accessor function for current stamin 
	UFUNCTION(BlueprintPure, Category = "Stamina")
	float GetCurrentStamina();

	//Update current Stamina in Blueprint
	UFUNCTION(BlueprintCallable, Category = "Stamina")
	void UpdateCurrentStamina(float Stamina);

	//Interaction funktionen

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUseItem OnUseItem;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	/*************************************************************************/
	#pragma region FNames_For_Subobjects
	/*************************************************************************/
	//Init Subobject Names

	const FName FN_ROOT		=	TEXT("Root Component");
	const FName FN_MESH		=	TEXT("Mesh");
	const FName FN_CAMERA	=	TEXT("Camera");
	const FName FN_MOVE		=	TEXT("Movement");
	#pragma endregion
	/*************************************************************************/
	#pragma region Paths
	/*************************************************************************/

	// PATHS 
	// S = SKELETAL
	// A = ANIMATION

	//Mesh-PATH
	const FString S_Mesh_PATH =
		TEXT("SkeletalMesh'/Game/Characters/Mannequins/MainPlayer/character.character'");

	//Animation-PATHS
	const FString A_Idel_up_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Offensive_Idle.Offensive_Idle'");

	//Walking

	const FString A_Walk_Forward_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Standard_Walk.Standard_Walk'");

	const FString A_Walk_Backwards_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Walking_Backwards.Walking_Backwards'");

	const FString A_Walk_Right_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Walk_Strafe_right.Walk_Strafe_right'");

	const FString A_Walk_Left_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Walk_Strafe_Left.Walk_Strafe_Left'");

	const FString A_Running_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Running.Running'");

	//Crouch_to_Stand

	const FString A_to_Stand_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_To_Standing_Idle.Crouch_To_Standing_Idle'");

	const FString A_to_Crouch_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Standing_Idle_To_Crouch.Standing_Idle_To_Crouch'");

	// Crouching

	const FString A_Idel_Crouch_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_Idle__1_.Crouch_Idle__1_'");

	const FString A_Crouch_Walk_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_Walk_Forward__1_.Crouch_Walk_Forward__1_'");

	const FString A_Crouch_Left_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_Walk_Left__1_.Crouch_Walk_Left__1_'");

	const FString A_Crouch_Right_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_Walk_Right__1_.Crouch_Walk_Right__1_'");

	const FString A_Crouch_Backwards_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Crouch_Walk_Back__1_.Crouch_Walk_Back__1_'");

	// Jumping

	const FString A_Jump_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Jump.Jump'");

	// Sneak Walk

	const FString A_Sneaky_PATH =
		TEXT("AnimSequence'/Game/Characters/Mannequins/MainPlayer/Animations/Sneak_Walk.Sneak_Walk'");

	#pragma endregion
	/*************************************************************************/
	#pragma region Values
	/*************************************************************************/

	//DEFAULTS INIT 

	const FRotator	DEFAULT_MESH_ROT	= FRotator	(0.0f, 0.0f, 0.0f);
	const FVector	DEFAULT_MESH_LOC	= FVector	(0.0f, 0.0f, 0.0f);

	const FRotator	DEFAULT_CAM_ROT		= FRotator	(0.0f, 0.0f, 0.0f);
	const FVector	DEFAULT_CAM_LOC		= FVector	(0.0f, 0.0f, 0.0f);
	
	const float		DEFAULT_ARM_LENGHT	=			     300.0f;

	const FRotator  DEFAULT_ARM_ROT		= FRotator	(-45.f, 0.f, 0.0f);

		//Axís Names

	const FName		FORWARD_AXIS		= TEXT	("Forward");
	const FName		RIGHT_AXIS			= TEXT	("Right");

	const FName		M_WHEEL_AXIS		= TEXT	("MouseWheel");

		//Input AXIS

	const float		POS_INPUT_SCALE		=	1.0f;
	const float		NEG_INPUT_SCALE		=  -1.0f;

	const float		M_W_POS_INPUT_SCALE =	1.0f;
	const float		M_W_NEG_INPUT_SCALE =  -1.0f;

		//INPUT BTN

	const FName	 MousePrimaryBTN		= TEXT ("Primary Action");
	const FName	 MouseSecondaryBTN		= TEXT ("Secondary Action");
	const FName	 MouseMiddleBTN			= TEXT ("Third Action");
	const FName	 JumpBTN				= TEXT ("Jump");
	const FName	 SprintBTN				= TEXT ("Sprint");
	const FName	 CameraToggle			= TEXT ("Camera Switch")

		//Speed

	const float		SPEED	= 300.0f;
	const float RUN_SPEED	= 600.0f;

	const float CLAMP_MAX	=  1.0f;
	const float CLAMP_MIN	= -1.0f;

	//Camera Arm Settings

	UPROPERTY(EditAnywhere, Category = "Settings")
	bool CameraLag = true;

	float CameraLagSpeed = 2.0f;

	float CameraLagMaxDistance = 1.5f;

	bool CameraRotationLag = true;

	float CameraRotationLagSpeed = 4.0f;

	float CameraLagMaxTime = 1.0f;

	//Stamina Values

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float initStamina = 420;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float currentStamina = 0;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float maxStamina = 420;

	UPROPERTY(EditAnywhere, Category = "Stamina")
	float minStamina = 0;

	//Animation Values

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation_Info")
	bool player_has_weapon = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation_Info")
	bool crouching = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation_Info")
	float verticalSpeed = 0.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation_Info")
	float horizontalSpeed = 0.0f;

	#pragma endregion
	/*************************************************************************/
	#pragma region Variables
	/*************************************************************************/


	//Animations Classes

	bool p_IsWalkingForward, p_IsWalkingRight = false;

	class UAnimaitonAsset* m_pIdelAnim = nullptr;
	class UAnimaitonAsset* m_pWalkingForwardAnim = nullptr;
	class UAnimaitonAsset* m_pWalkingRightAnim = nullptr;
	class UAnimaitonAsset* m_pWalkingLeftAnim = nullptr;
	class UAnimationAsset* m_pWalkingBackwardsAnim = nullptr;

	class UAnimaitonAsset* m_pJumpingAnim = nullptr;

	class UAnimaitonAsset* m_pCrouchIdelAnim = nullptr;
	class UAnimaitonAsset* m_pCrouchingForwardAnim = nullptr;
	class UAnimaitonAsset* m_pCrouchingRightAnim = nullptr;
	class UAnimaitonAsset* m_pCrouchingLeftAnim = nullptr;
	class UAnimationAsset* m_pCrouchingBackwards = nullptr;

	class UAnimationAsset* m_pSneakWalkAnim = nullptr;

	class UAnimationAsset* m_pStandToCrouchAnim = nullptr;
	class UAnimationAsset* m_pCrouchToStandAnim = nullptr;

	//Mesh Player-Character

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Mesh",
				Category = "Component"))

		class USkeletalMeshComponent* m_pMesh = nullptr;

	//SpringArm

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "SpringArm",
				Category = "Component"))

		class USpringArmComponent* m_pArm = nullptr;


	//Camera
	
	UPROPERTY(EditAnywhere,
		meta(DisplayName = "Camera",
			 Category = "Component"))

		class UCameraComponent* m_pCamera = nullptr;

	//Movement

	UPROPERTY(EditAnywhere,
		meta = (DisplayName = "Movement",
				Category = "Component"))

		class UFloatingPawnMovement* m_pMovement = nullptr;



	//Keyboard INPUT
	void MoveHorizontal(float value);
	void StopMoveHorizontal();
	void MoveVertical(float value);
	void StopMoveVertical();

	void CheckJump();
	void SwitchCamera();
	void Sprint();



	//Mouse INPUT
	void RotHorizontal(float value);
	void RotVertical(float value);
	void MouseWeehl(float value);
	void MouseWeehlToggle();

	void OnPrimaryAction();
	void OnSecondaryAction();

	UPROPERTY()
	bool walking = false;

	UPROPERTY()
	float speed = 1.0f;

	UPROPERTY()
	bool firstPerson = false;

	UPROPERTY()
	bool zoomOrWpn = false;

	UPROPERTY()
	UCapsuleComponent* collision = nullptr;

	UPROPERTY()
	bool jumping = false;

	#pragma endregion
	/*************************************************************************/
};
